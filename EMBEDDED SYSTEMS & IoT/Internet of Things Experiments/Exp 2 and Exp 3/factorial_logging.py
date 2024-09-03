import logging

# Set up basic logging configuration
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

def factorial(n):
    logging.debug(f'Starting factorial calculation for n={n}')
    if n == 1:
        logging.debug(f'Base case reached with n={n}')
        return 1
    else:
        result = n * factorial(n - 1)
        logging.debug(f'Computed factorial({n}) = {result}')
        return result

if __name__ == "__main__":
    number = 5  # You can change this number to test other values
    logging.info(f'Calculating factorial for {number}')
    result = factorial(number)
    logging.info(f'Factorial of {number} is {result}')
    print(f'Factorial of {number} is {result}')

