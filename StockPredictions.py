def printTransactions(m, k, d, name, owned, prices):
    transactions = []
    
    # Process SELL transactions
    for i in range(k):
        current_price = prices[i][-1]
        max_price = max(prices[i])
        if current_price == max_price and owned[i] > 0:
            transactions.append((name[i], 'SELL', owned[i]))
    
    # Process BUY transactions
    available = m
    for i in range(k):
        current_price = prices[i][-1]
        min_price = min(prices[i])
        if current_price == min_price:
            if available >= current_price - 1e-9:  # Handling floating point precision
                max_shares = int(available // current_price)
                if max_shares > 0:
                    transactions.append((name[i], 'BUY', max_shares))
                    available -= max_shares * current_price
    
    # Output the transactions
    print(len(transactions))
    for transaction in transactions:
        print(f"{transaction[0]} {transaction[1]} {transaction[2]}")

if __name__ == "__main__":
    import sys
    input_lines = [line.strip() for line in sys.stdin]
    ptr = 0
    m, k, d = map(float, input_lines[ptr].split())
    m = float(m)
    k = int(k)
    d = int(d)
    ptr += 1
    
    names = []
    owned = []
    stock_prices = []
    
    for _ in range(k):
        parts = input_lines[ptr].split()
        ptr += 1
        names.append(parts[0])
        owned.append(int(parts[1]))
        prices = list(map(float, parts[2:7]))
        stock_prices.append(prices)
    
    printTransactions(m, k, d, names, owned, stock_prices)
