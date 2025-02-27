import random
import argparse

def main():
    parser = argparse.ArgumentParser(description='Generate and shuffle a list of numbers.')
    parser.add_argument('count', type=int, help='The number of random numbers to generate')
    parser.add_argument('min_value', type=int, help='The minimum value for the random numbers')
    parser.add_argument('max_value', type=int, help='The maximum value for the random numbers')
    args = parser.parse_args()

    # numbers = random.sample(range(-2147483648, 2147483647), args.count)
    numbers = random.sample(range(args.min_value, args.max_value + 1), args.count)
    random.shuffle(numbers)
    print(' '.join(map(str, numbers)))

if __name__ == '__main__':
    main()