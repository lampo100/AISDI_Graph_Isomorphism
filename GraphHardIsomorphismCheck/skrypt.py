file_anchor = open('Graph1', 'w')
file_anchor2 = open('Graph1', 'w')
file_anchor.write('100\n')
file_anchor2.write('100\n')

for i in range(0, 100):
    file_anchor.write(str(i) + ' ' + str((i + 1) % 100) + '\n')
    file_anchor2.write(str(i) + ' ' + str((i + 1) % 100) + '\n')
file_anchor.close()
file_anchor2.close()
