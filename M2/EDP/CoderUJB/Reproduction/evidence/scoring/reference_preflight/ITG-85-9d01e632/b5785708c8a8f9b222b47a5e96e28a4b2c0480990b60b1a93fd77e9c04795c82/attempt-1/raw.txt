    public void testBug1864222() {
        TimeSeries s = new TimeSeries("S");
        s.add(new Day(19, 8, 2005), 1);
        s.add(new Day(31, 1, 2006), 1);
        boolean pass = true;
        try {
            s.createCopy(new Day(1, 12, 2005), new Day(18, 1, 2006));
        }
        catch (CloneNotSupportedException e) {
            pass = false;
        }
        assertTrue(pass);
    }