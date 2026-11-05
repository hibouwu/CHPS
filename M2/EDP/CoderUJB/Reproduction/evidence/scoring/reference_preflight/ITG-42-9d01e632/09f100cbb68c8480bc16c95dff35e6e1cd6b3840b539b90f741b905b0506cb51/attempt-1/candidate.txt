    public void testEqualsAfterSerializationOfDerivedClass() throws IOException, ClassNotFoundException
    {
        final DerivedMultiKey<?> mk = new DerivedMultiKey<String>("A", "B");

        // serialize
        final ByteArrayOutputStream baos = new ByteArrayOutputStream();
        final ObjectOutputStream out = new ObjectOutputStream(baos);
        out.writeObject(mk);
        out.close();

        // deserialize
        final ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());
        final ObjectInputStream in = new ObjectInputStream(bais);
        final DerivedMultiKey<?> mk2 = (DerivedMultiKey<?>)in.readObject();
        in.close();

        assertEquals(mk.hashCode(), mk2.hashCode());
    }