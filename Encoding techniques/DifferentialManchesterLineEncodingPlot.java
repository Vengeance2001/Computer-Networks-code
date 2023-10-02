import javax.swing.*;
import java.awt.*;

public class DifferentialManchesterLineEncodingPlot extends JFrame {
    private String signal;
    private int pos_x = 50, pos_y = 100;
    private int base = 0, distance = 20;
    private int logic_high = 20, logic_low = -20; // Flipped logic levels compared to Manchester

    public DifferentialManchesterLineEncodingPlot(String signal) {
        this.signal = signal;
        setTitle("Differential Manchester Line Encoding Signal");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setPreferredSize(new Dimension(800, 200));
        pack();
        setLocationRelativeTo(null);
    }

    public void paint(Graphics g) {
        super.paint(g);

        for (char c : signal.toCharArray()) {
            if (c == '1') {
                one();
            } else if (c == '0') {
                zero();
            } else {
                invalid();
            }
        }
    }

    private void signalMove(int offset_x, int offset_y) {
        Graphics g = getGraphics();
        g.drawLine(pos_x, pos_y, pos_x + offset_x, pos_y + offset_y);
        pos_x += offset_x;
        pos_y += offset_y;
    }

    private void signalShift(int new_x, int new_y) {
        Graphics g = getGraphics();
        g.drawLine(pos_x, pos_y, new_x, new_y);
        pos_x = new_x;
        pos_y = new_y;
    }

    private void drawAxes() {
        Graphics g = getGraphics();
        g.drawLine(0, pos_y, 640, pos_y);
        g.drawLine(pos_x, 0, pos_x, 200);
    }

    private void initGraph() {
        Graphics g = getGraphics();
        drawAxes();
        g.setColor(Color.RED);
    }

    private void zero() {
        int current_x = pos_x;
        int current_y = pos_y;

        // First half of '0' bit (positive-to-negative transition)
        signalMove(distance / 2, 0);
        signalMove(0, logic_high);
        signalMove(distance / 2, 0);
        signalMove(0, logic_low);

        int new_x = pos_x;
        int new_y = pos_y;

        signalShift(current_x, current_y);
        signalMove(distance, 0);

        current_x = pos_x;
        current_y = pos_y;

        // Second half of '0' bit (negative-to-positive transition)
        signalMove(0, logic_low);
        signalMove(distance / 2, 0);
        signalMove(0, logic_high);
        signalMove(distance / 2, 0);

        int second_half_new_x = pos_x;
        int second_half_new_y = pos_y;

        Graphics g = getGraphics();
        g.drawLine(new_x, new_y, second_half_new_x, second_half_new_y);

        signalShift(second_half_new_x, second_half_new_y);
    }

    private void one() {
        int current_x = pos_x;
        int current_y = pos_y;

        // First half of '1' bit (negative-to-positive transition)
        signalMove(distance / 2, 0);
        signalMove(0, logic_low);
        signalMove(distance / 2, 0);
        signalMove(0, logic_high);

        int new_x = pos_x;
        int new_y = pos_y;

        signalShift(current_x, current_y);
        signalMove(distance, 0);

        current_x = pos_x;
        current_y = pos_y;

        // Second half of '1' bit (positive-to-negative transition)
        signalMove(0, logic_high);
        signalMove(distance / 2, 0);
        signalMove(0, logic_low);
        signalMove(distance / 2, 0);

        int second_half_new_x = pos_x;
        int second_half_new_y = pos_y;

        Graphics g = getGraphics();
        g.drawLine(new_x, new_y, second_half_new_x, second_half_new_y);

        signalShift(second_half_new_x, second_half_new_y);
    }

    private void invalid() {
        // Handle invalid input characters if necessary
    }

    public static void main(String[] args) {
        String signal = JOptionPane.showInputDialog("Enter signal to be encoded");

        SwingUtilities.invokeLater(() -> {
            DifferentialManchesterLineEncodingPlot plot = new DifferentialManchesterLineEncodingPlot(signal);
            plot.setVisible(true);
            plot.initGraph();
        });
    }
}
