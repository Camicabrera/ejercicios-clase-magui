def minimize_cash_flow(debt):
    return ""

# Tests
debt1 = [
    [0, 1000, 2000],
    [0, 0, 5000],
    [0, 0, 0]
]
result1 = minimize_cash_flow(debt1)
expected1 = [
    "Amigo 1 paga 3000 a Amigo 2",
    "Amigo 0 paga 2000 a Amigo 2",
    "Amigo 0 paga 1000 a Amigo 1"
]
for res in expected1:
    assert res in result1

debt2 = [
    [0, 100, 200],
    [100, 0, 300],
    [200, 0, 0]
]
result2 = minimize_cash_flow(debt2)
expected2 = [
    "Amigo 1 paga 100 a Amigo 2",
    "Amigo 0 paga 300 a Amigo 2"
]
for res in expected2:
    assert res in result2

print("Todos los tests pasaron.")
