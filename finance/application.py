from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.globals.update(usd=usd)
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    user_stocks = db.execute(
        "SELECT name, sum(amount) FROM transactions WHERE user_id = :user_id GROUP BY name",user_id=session["user_id"])
    user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    stock_sum = 0
     # https://stackoverflow.com/questions/1235618/python-remove-dictionary-from-list come back to this
    user_stocks[:] = [a for a in user_stocks if a.get('sum(amount)') != 0]
    for stock in user_stocks:
        stock["price"] = round(lookup(stock["name"])["price"], 2)
        stock["value"] = round(stock["sum(amount)"] * stock["price"], 2)
        stock_sum += stock["value"]

    grand_total = round(user_cash[0]["cash"] + stock_sum, 2)
    return render_template("index.html", user_stocks=user_stocks, user_cash=user_cash[0]["cash"], grand_total=grand_total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not lookup(request.form.get("symbol")):
            return apology("Could not find stock")
        elif not request.form.get("shares"):
            return apology("can't buy ZERO shares my friend")
        elif not request.form.get("shares").isdigit() >= 1:
            return apology("must be positive integer", 400)

        else:
            share = lookup(request.form.get("symbol"))
            user_cash = db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
            if user_cash[0]["cash"] < share["price"] * int(request.form.get("shares")):
                return apology("Sorry you are to poor")
            else:
                db.execute("INSERT INTO transactions (user_id, name, price, amount, transaction_type) VALUES(:user_id, :name, :price, :amount, :transaction_type)",
                            user_id=session["user_id"], name=share["symbol"], price=share["price"], amount=int(request.form.get("shares")), transaction_type="buy")

                db.execute("UPDATE users SET cash = :updated_cash WHERE id = :user_id", updated_cash=user_cash[0]["cash"] - (share["price"] * int(request.form.get("shares"))),
                user_id=session["user_id"])
                return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Provide sotck name", 400)
        else:
            quote = lookup(request.form.get("symbol"))
            if not quote:
                return apology("Could not find stock", 400)
            else:
                return render_template("quoted.html",name=quote["symbol"], price=usd(quote["price"]))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Missing username", 400)
        if not request.form.get("password"):
            return apology("Missing password", 400)
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords do not match", 400)
        else:
            password_hash = generate_password_hash(request.form.get("password"))
            # store user into database
            result=db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                            username = request.form.get("username"), hash=password_hash)
            if not result:
                return apology ("Username already exists", 400)
            # get the user id and store it into session
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get("username"))
            session["user_id"] = rows[0]["id"]
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        name = request.form.get("symbol")
        if not request.form.get("shares").isdigit() >= 1:
            return apology("must be positive integer", 400)
        amount_to_sell = int (request.form.get("shares"))
        amount_user = db.execute("SELECT sum(amount) FROM transactions WHERE user_id = :user_id AND name = :name",user_id=session["user_id"], name=name )
        if amount_user[0]["sum(amount)"] <  amount_to_sell:
            return apology("you don't have that many stocks")
        else:
            share = lookup(name)
            db.execute("INSERT INTO transactions (user_id, name, price, amount, transaction_type) VALUES(:user_id, :name, :price, :amount, :transaction_type)",
                        user_id=session["user_id"], name=share["name"], price=share["price"], amount=-amount_to_sell, transaction_type="sell")
            user_cash = db.execute("SELECT cash FROM users WHERE id= :id",id=session["user_id"])
            db.execute("UPDATE users SET cash = :updated_cash WHERE id = :user_id", updated_cash=user_cash[0]["cash"] + (share["price"] * amount_to_sell),
                user_id = session["user_id"])
            user_cash = db.execute("SELECT cash FROM users WHERE id= :id",id=session["user_id"])
            return render_template("sold.html", name=share["name"], price=share["price"], shares=amount_to_sell, value=share["price"] * amount_to_sell, cash=user_cash[0]["cash"])
    else:
        user_stocks = db.execute("SELECT name, sum(amount) FROM transactions WHERE user_id = :user_id GROUP BY name",user_id=session["user_id"])
        user_stocks[:] = [a for a in user_stocks if a.get('sum(amount)') != 0]
        return render_template("sell.html", user_stocks=user_stocks)

@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "POST":
        if not request.form.get("password"):
            return apology("Missing password", 400)
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords do not match", 400)
        else:
            password_hash = generate_password_hash(request.form.get("password"))
            # store user into database
            result = db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", hash=password_hash, user_id=session["user_id"])
            return redirect("/")
    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
