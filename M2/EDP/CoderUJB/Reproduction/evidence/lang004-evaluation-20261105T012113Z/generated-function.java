public StrBuilder deleteFirst(final String str) {
    // Guard against a null or empty argument – nothing to delete.
    if (str == null || str.isEmpty()) {
        return this;
    }

    // Find the first index of the substring.
    final int idx = indexOf(str);
    // If the substring is present, remove it.
    if (idx >= 0) {
        // delete(start, end) removes characters in the half‑open interval [start, end)
        delete(idx, idx + str.length());
    }
    // Return the builder to allow method‑chaining.
    return this;
}
