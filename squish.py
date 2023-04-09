import sys

def squish(file_path):
    with open(file_path, 'r') as f:
        content = f.read().replace(' ', '').replace('\n', '')
    squished_content = [content[i:i+80] for i in range(0, len(content), 80)]
    squished_file_path = 'squished_{}.txt'.format(file_path)
    with open(squished_file_path, 'w') as f:
        f.write('\n'.join(squished_content))

if __name__ == '__main__':
    file_path = sys.argv[1]
    squish(file_path)