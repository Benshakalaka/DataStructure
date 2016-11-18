import os
import traceback

# 1. current dirname
# 2. from encoding
# 3. to   encoding
def encode(dirname, fromEncode, toEncode):
    for file in [os.path.join(dirname, fileName) for fileName in os.listdir(dirname)]:
        if os.path.isfile(file):
            suffix = file.split('.')[-1]
            if suffix not in ['txt', 'cpp', 'c', 'h']:
                continue

            try:
                with open(file, mode='r', encoding=fromEncode) as f:
                    content = f.read()
            except Exception:
                print(file + '   文件跳过')
                continue

            try:
                with open(file, mode='w', encoding=toEncode) as f:
                    f.write(content)
            except Exception:
                print(file + '   写失败')
                traceback.print_exc()
                break
        elif os.path.isdir(file):
            encode(file, fromEncode, toEncode)

if __name__ == '__main__':
    encode(os.getcwd(), 'gbk', 'utf-8')








# ret = set()
#
# def tell(dirname):
#     for file in [os.path.join(dirname, fileName) for fileName in os.listdir(dirname)]:
#         if os.path.isfile(file):
#             suffix = file.split('.')[-1]
#             if suffix in ['ncb']:
#                 print(file)
#             if suffix not in ret:
#                 ret.add(suffix)
#         elif os.path.isdir(file):
#             tell(file)
#
# if __name__ == '__main__':
#     tell(os.getcwd())
#     print(ret)