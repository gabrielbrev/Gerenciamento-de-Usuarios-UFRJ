def values(data):
    if isinstance(data, list) or isinstance(data, tuple):
        for value in data:
            values(value)
        return
    elif isinstance(data, dict):
        for value in data.values():
            values(value)
        return
    else:
        print(data)
    
    