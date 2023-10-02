public class hammingS {
    public static String encode(String message) {
        int m = message.length();
        int r = 0;
        while (Math.pow(2, r) < (m + r + 1)) {
            r++;
        }
        int n = m + r;
        StringBuilder encodedMessage = new StringBuilder();

        for (int i = 0, j = 0; i < n; i++) {
            if (i + 1 == Math.pow(2, j)) {
                encodedMessage.append('0'); 
                j++;
            } else {
                encodedMessage.append(message.charAt(i - j));
            }
        }

        for (int i = 0; i < r; i++) {
            int parityBitPosition = (int) Math.pow(2, i);
            char parity = calculateParity(encodedMessage, parityBitPosition);
            encodedMessage.setCharAt(parityBitPosition - 1, parity);
        }

        return encodedMessage.toString();
    }

    private static char calculateParity(StringBuilder message, int parityBitPosition) {
        int count = 0;
        for (int i = parityBitPosition - 1; i < message.length(); i += 2 * parityBitPosition) {
            for (int j = i; j < i + parityBitPosition && j < message.length(); j++) {
                if (message.charAt(j) == '1') {
                    count++;
                }
            }
        }
        return (count % 2 == 0) ? '0' : '1';
    }

    public static void main(String[] args) {
        String message = "1101"; 
        String encodedMessage = encode(message);
        System.out.println("Encoded Message: " + encodedMessage);
    }
}