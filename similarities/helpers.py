from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    matrix = [[(0, 0) for i in range(len(b) + 1)]for j in range(len(a) + 1)]
    matrix[0][0] = (0, None)
    for i in range(len(a)):
        matrix[i + 1][0] = (i + 1, Operation.DELETED)

    for j in range(len(b)):
        matrix[0][j + 1] = (j + 1, Operation.INSERTED)
    for i, row in enumerate(matrix):
        for j, item in enumerate(row):
            if i > 0 and j > 0:
                matrix[i][j] = cost(matrix[i][j][0], a, b, matrix, i, j)
    return matrix


def cost(a, str1, str2, matrix, i, j):
    deletion = matrix[i - 1][j][0] + 1
    insertion = matrix[i][j - 1][0] + 1
    if str1[i - 1] == str2[j - 1]:
        substitution = matrix[i - 1][j - 1][0]
    else:
        substitution = matrix[i - 1][j - 1][0] + 1
    if min(deletion, insertion, substitution) == deletion:
        return(deletion, Operation.DELETED)
    elif min(deletion, insertion, substitution) == insertion:
        return(insertion, Operation.INSERTED)
    else:
        return(substitution, Operation.SUBSTITUTED)