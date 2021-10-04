def find_prime_factors(n):
    i = 2
    factors = []
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors

if __name__ == "__main__":
    for n in [ 2009, 720720, 999983 ]:
        s=str(n)+" = 1"
        for p in find_prime_factors(n):
            s=s+" * "+str(p)
        print(s)