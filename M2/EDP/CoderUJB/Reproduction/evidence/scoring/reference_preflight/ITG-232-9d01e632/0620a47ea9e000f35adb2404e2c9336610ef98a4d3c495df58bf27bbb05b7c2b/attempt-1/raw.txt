    public void testCodec112() { // size calculation assumes always chunked
        byte[] in = new byte[] {0};
        byte[] out=Base64.encodeBase64(in);
        Base64.encodeBase64(in, false, false, out.length);
    }