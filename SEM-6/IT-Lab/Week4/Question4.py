class Question4:
    '''This is a class to get and print string in upper case'''
    str = ""
    def get_String(self):
        self.str = input('Enter a string: ')
    def print_String(self):
        print(self.str.upper())
        return
question4 = Question4()
question4.get_String()
question4.print_String()