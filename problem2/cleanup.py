# SOURCE: http://stackoverflow.com/questions/11968998/remove-lines-that-contain-certain-string

bad_words = ['basic_string','%','@plt>']


with open('original.txt') as oldfile, open('output.txt', 'w') as newfile:
    for line in oldfile:
        if not any(bad_word in line for bad_word in bad_words):
            newfile.write(line)