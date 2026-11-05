    public StrBuilder deleteFirst(final String str) {

        if (str == null) {
            return this;
        }
        final int len = str.length();
        if (len == 0) {
            return this;
        }
        int index = indexOf(str);
        if (index >= 0) {
            delete(index, index + len);
        }
        return this;
    }
