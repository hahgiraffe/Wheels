String类的初步实现,有三种实现方式
（1）无特殊处理，eager copy
（2）copy on write
（3）短字符串优化，利用string对象本身的空间存储短字符串