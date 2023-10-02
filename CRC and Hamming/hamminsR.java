public class hamminsR {
    public static String decode(String receivedMessage) {
        int n = receivedMessage.length();
        int r = 0;
        while (Math.pow(2, r) < n) {
            r++;
        }
        int m = n - r;
        StringBuilder decodedMessage = new StringBuilder();

        for (int i = 0, j = 0; i < n; i++) {
            if (i + 1 != Math.pow(2, j)) {
                decodedMessage.append(receivedMessage.charAt(i));
            } else {
                j++;
            }
        }

        int errorPosition = checkParity(receivedMessage);
        if (errorPosition != -1) {
            System.out.println("Error detected at position: " + errorPosition);
            decodedMessage.setCharAt(errorPosition - 1, (decodedMessage.charAt(errorPosition - 1) == '0') ? '1' : '0');
        }

        return decodedMessage.toString().substring(0, m);
    }

    private static int checkParity(String receivedMessage) {
        int r = 0;
        while (Math.pow(2, r) <= receivedMessage.length()) {
            r++;
        }
        int errorPosition = 0;

        for (int i = 0; i < r; i++) {
            int parityBitPosition = (int) Math.pow(2, i);
            int count = 0;

            for (int j = parityBitPosition - 1; j < receivedMessage.length(); j += 2 * parityBitPosition) {
                for (int k = j; k < j + parityBitPosition && k < receivedMessage.length(); k++) {
                    if (receivedMessage.charAt(k) == '1') {
                        count++;
                    }
                }
            }

            if (count % 2 != 0) {
                errorPosition += parityBitPosition;
            }
        }

        return (errorPosition == 0) ? -1 : errorPosition;
    }

    public static void main(String[] args) {
        String receivedMessage = "1011101"; 
        String decodedMessage = decode(receivedMessage);
        System.out.println("Decoded Message: " + decodedMessage);
    }
}