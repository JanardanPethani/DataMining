my_dict = {0: ['i1', 'i3', 'i2'], 'Kenneth Love': ['i1', 'i2']}


def most_classes(my_dict):
    max_count = 0
    max_class_teacher = ""
    for key, value in my_dict.items():
        temp_count = len(list(filter(i1, value)))
        print(value, temp_count)
        if max_count < temp_count:
            max_count = temp_count
            max_class_teacher = key
    return max_count


print(most_classes(my_dict))
