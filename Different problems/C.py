from decimal import Decimal as D


def find_intersection(xA: D, yA: D, xB: D, yB: D, xC: D, yC: D, xD: D, yD: D):
    m_AB = (yB - yA) / (xB - xA)
    b_AB = yA - m_AB * xA

    m_CD = (yD - yC) / (xD - xC)
    b_CD = yC - m_CD * xC

    if abs(m_AB - m_CD) <= 1e-9:
        if abs(b_AB - b_CD) <= 1e-9:
            return "Infinity"
        else:
            return "No"
    else:
        xM = (b_CD - b_AB) / (m_AB - m_CD)
        yM = m_AB * xM + b_AB

        if (min(xA, xB) <= xM <= max(xA, xB)) and (min(xC, xD) <= xM <= max(xC, xD)):
            return f"{xM} {yM:.9f}"
        else:
            return "No"


# Пример использования
xA, yA, xB, yB = map(D, input().split())
xC, yC, xD, yD = map(D, input().split())

result = find_intersection(xA, yA, xB, yB, xC, yC, xD, yD)
print(result)
