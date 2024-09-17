import random

def generate_cache_test(capacity, num_elements, element_range):
    test_string = f"{capacity} {num_elements} "
    
    elements = [str(random.randint(1, element_range)) for _ in range(num_elements)]
    
    test_string += ' '.join(elements)
    
    return test_string

if __name__ == "__main__":
    capacity = int(input("Enter cache capacity: "))
    num_elements = int(input("Enter number of elements: "))
    element_range = int(input("Enter range of elements (e.g., 10 for range 1-10): "))
    file_name = input("Enter the name of the output file (e.g., test.txt): ")

    test_string = generate_cache_test(capacity, num_elements, element_range)

    file = open(file_name, 'w')
    file.write(test_string)
    file.close()  
    
    print(f"Test string successfully written to {file_name}")
