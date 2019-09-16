from tkinter import *
from tkinter.ttk import *
import threading
import time


def int_to_status(num):
    if num == 0:
        return "I"
    if num == 1:
        return "S"
    else:
        return "M"

f = open("info_for_ui/cache0_content.txt", "w")
if f.mode == 'w':
    f.write("[[0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0]]")
    f.close()

f = open("info_for_ui/cache1_content.txt", "w")
if f.mode == 'w':
    f.write("[[0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0]]")
    f.close()

f = open("info_for_ui/cache2_content.txt", "w")
if f.mode == 'w':
    f.write("[[0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0]]")
    f.close()

f = open("info_for_ui/cache3_content.txt", "w")
if f.mode == 'w':
    f.write("[[0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0]]")
    f.close()

f = open("info_for_ui/memory_content.txt", "w")
if f.mode == 'w':
    f.write("[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]")
    f.close()

f = open("info_for_ui/cache0_info.txt", "w")
if f.mode == 'w':
    f.close()

f = open("info_for_ui/cache1_info.txt", "w")
if f.mode == 'w':
    f.close()

f = open("info_for_ui/cache2_info.txt", "w")
if f.mode == 'w':
    f.close()

f = open("info_for_ui/cache3_info.txt", "w")
if f.mode == 'w':
    f.close()

main = Tk()
main.title("Multiprocessor UI")

main.grid_rowconfigure(0, weight=1)
main.grid_columnconfigure(0, weight=1)
main.grid_rowconfigure(1, weight=1)
main.grid_columnconfigure(1, weight=1)

core0_label = Label(main, text="Core 1 Cache", font=("Arial", 30)).grid(row=0, column=0, sticky="n", columnspan=3)
core1_label = Label(main, text="Core 2 Cache", font=("Arial", 30)).grid(row=0, column=3, sticky="n", columnspan=3)
core2_label = Label(main, text="Core 3 Cache", font=("Arial", 30)).grid(row=2, column=0, sticky="n", columnspan=3)
core3_label = Label(main, text="Core 4 Cache", font=("Arial", 30)).grid(row=2, column=3, sticky="n", columnspan=3)
mem_label = Label(main, text="Memory", font=("Arial", 30)).grid(row=0, column=6, sticky="n", columnspan=2)



# create Treeview with 3 columns
cols = ('Block','Tag', 'Value', 'Status')
tree0 = Treeview(main, columns=cols, show='headings', selectmode="extended", height=8)
for col in cols:
    tree0.heading(col, text=col)
tree0.grid(row=1, column=0)
tree0.column('Block', minwidth=0, width=48, stretch=NO)
tree0.column('Tag', minwidth=0, width=48, stretch=NO)
tree0.column('Value', minwidth=0, width=48, stretch=NO)
tree0.column('Status', minwidth=0, width=48, stretch=NO)


tree0_info = Treeview(main, columns=["CacheInfo"], show='headings', selectmode="extended", height=8)
tree0_info.heading('CacheInfo', text='Cache Info')
tree0_info.grid(row=1, column=1, padx = 10, pady = 10)
tree0_info.column('CacheInfo', minwidth=0, width=320, stretch=NO)



tree1 = Treeview(main, columns=cols, show='headings', selectmode="extended", height=8)
for col in cols:
    tree1.heading(col, text=col)
tree1.grid(row=1, column=3)
tree1.column('Block', minwidth=0, width=48, stretch=NO)
tree1.column('Tag', minwidth=0, width=48, stretch=NO)
tree1.column('Value', minwidth=0, width=48, stretch=NO)
tree1.column('Status', minwidth=0, width=48, stretch=NO)

tree1_info = Treeview(main, columns=["CacheInfo"], show='headings', selectmode="extended", height=8)

tree1_info.heading('CacheInfo', text='Cache Info')
tree1_info.grid(row=1, column=4, padx = 10, pady = 10)
tree1_info.column('CacheInfo', minwidth=0, width=320, stretch=NO)


tree2 = Treeview(main, columns=cols, show='headings', selectmode="extended", height=8)
for col in cols:
    tree2.heading(col, text=col)
tree2.grid(row=3, column=0)
tree2.column('Block', minwidth=0, width=48, stretch=NO)
tree2.column('Tag', minwidth=0, width=48, stretch=NO)
tree2.column('Value', minwidth=0, width=48, stretch=NO)
tree2.column('Status', minwidth=0, width=48, stretch=NO)

tree2_info = Treeview(main, columns=["CacheInfo"], show='headings', selectmode="extended", height=8)

tree2_info.heading('CacheInfo', text='Cache Info')
tree2_info.grid(row=3, column=1, padx = 10, pady = 10)
tree2_info.column('CacheInfo', minwidth=0, width=320, stretch=NO)


tree3 = Treeview(main, columns=cols, show='headings', selectmode="extended", height=8)
for col in cols:
    tree3.heading(col, text=col)
tree3.grid(row=3, column=3)
tree3.column('Block', minwidth=0, width=48, stretch=NO)
tree3.column('Tag', minwidth=0, width=48, stretch=NO)
tree3.column('Value', minwidth=0, width=48, stretch=NO)
tree3.column('Status', minwidth=0, width=48, stretch=NO)

tree3_info = Treeview(main, columns=["CacheInfo"], show='headings', selectmode="extended", height=8)

tree3_info.heading('CacheInfo', text='Cache Info')
tree3_info.grid(row=3, column=4, padx = 10, pady = 10)
tree3_info.column('CacheInfo', minwidth=0, width=320, stretch=NO)


cols_mem = ('Address', 'Value')
tree_mem = Treeview(main, columns=cols_mem, show='headings', selectmode="extended", height=16)
for col in cols_mem:
    tree_mem.heading(col, text=col)
tree_mem.grid(row=1, column=6, rowspan = 3,padx=20, pady=20)
tree_mem.column('Address', minwidth=0, width=64, stretch=NO)
tree_mem.column('Value', minwidth=0, width=64, stretch=NO)


# core0_canvas = Canvas(main, height=165, bg="grey").grid(row=1, column=1)
# core1_canvas = Canvas(main, height=165, bg="grey").grid(row=1, column=4)
# core2_canvas = Canvas(main, height=165, bg="grey").grid(row=3, column=1)
# core3_canvas = Canvas(main, height=165, bg="grey").grid(row=3, column=4)

last_info0 = ""
last_info1 = ""
last_info2 = ""
last_info3 = ""


def update_tables():
    global last_info0, last_info1, last_info2, last_info3
    try:

        f = open("info_for_ui/cache0_content.txt", "r")
        if f.mode == 'r':
            contents = f.read()
            f.close()
            temp_list = eval(contents)

            tree0.delete(*tree0.get_children())

            for i in range(len(temp_list[0])):
                tree0.insert("", i, text=str(i), values=(i,temp_list[2][i], temp_list[0][i], int_to_status(temp_list[1][i])))


        f = open("info_for_ui/cache0_info.txt", "r")

        if f.mode == 'r':
            contents = f.read()
            f.close()
            if contents != last_info0:
                tree0_info.insert("", 0, text=str(i), values=[contents])
                last_info0 = contents

        f = open("info_for_ui/cache1_content.txt", "r")
        if f.mode == 'r':
            contents = f.read()
            f.close()
            temp_list = eval(contents)
            tree1.delete(*tree1.get_children())
            for i in range(len(temp_list[0])):
                tree1.insert("", i, text=str(i), values=(i,temp_list[2][i], temp_list[0][i], int_to_status(temp_list[1][i])))


        f = open("info_for_ui/cache1_info.txt", "r")

        if f.mode == 'r':
            contents = f.read()
            f.close()
            if contents != last_info1:
                tree1_info.insert("", 0, text=str(i), values=[contents])
                last_info1 = contents

        f = open("info_for_ui/cache2_content.txt", "r")
        if f.mode == 'r':
            contents = f.read()
            f.close()
            temp_list = eval(contents)
            tree2.delete(*tree2.get_children())

            for i in range(len(temp_list[0])):
                tree2.insert("", i, text=str(i), values=(i,temp_list[2][i], temp_list[0][i], int_to_status(temp_list[1][i])))

        f = open("info_for_ui/cache2_info.txt", "r")

        if f.mode == 'r':
            contents = f.read()
            f.close()
            if contents != last_info2:
                tree2_info.insert("", 0, text=str(i), values=[contents])
                last_info2 = contents

        f = open("info_for_ui/cache3_content.txt", "r")
        if f.mode == 'r':
            contents = f.read()
            f.close()
            temp_list = eval(contents)
            tree3.delete(*tree3.get_children())

            for i in range(len(temp_list[0])):
                tree3.insert("", i, text=str(i), values=(i,temp_list[2][i], temp_list[0][i], int_to_status(temp_list[1][i])))

        f = open("info_for_ui/cache3_info.txt", "r")

        if f.mode == 'r':
            contents = f.read()
            f.close()
            if contents != last_info3:
                tree3_info.insert("", 0, text=str(i), values=[contents])
                last_info3 = contents

        f = open("info_for_ui/memory_content.txt", "r")
        if f.mode == 'r':
            contents = f.read()
            f.close()
            temp_list = eval(contents)
            tree_mem.delete(*tree_mem.get_children())

            for i in range(len(temp_list)):
                tree_mem.insert("", i, text=str(i), values=(i,temp_list[i]))
    except:
        pass

    main.after(5, update_tables)


update_tables()

main.mainloop()

# x = threading.Thread(target=update_tables(), args=())
# x.start()