    public void testEmptyNodeSetOperations() {
        assertXPathValue(context, "/idonotexist = 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "/idonotexist != 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "/idonotexist < 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "/idonotexist > 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "/idonotexist >= 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "/idonotexist <= 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "$array[position() < 1] = 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "$array[position() < 1] != 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "$array[position() < 1] < 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "$array[position() < 1] > 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "$array[position() < 1] >= 0", Boolean.FALSE, Boolean.class);
        assertXPathValue(context, "$array[position() < 1] <= 0", Boolean.FALSE, Boolean.class);
    }