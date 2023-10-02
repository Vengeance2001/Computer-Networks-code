// Contains Unipolar, Polar and Bipolar (RZ + NRZ)

import javax.swing.*;
import java.awt.*;

public class BipolarLineEncodingPlot extends JFrame {
    private String signal;
    private int pos_x = 50, pos_y = 100;
    private int logic_high = -20, logic_low = 20;
    private int base = 0, distance = 20;

    public BipolarLineEncodingPlot(String signal) {
        this.signal = signal;
        setTitle("Bipolar Line Encoding Signal");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setPreferredSize(new Dimension(800, 500));
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
        // g.setColor(Color.RED);
    }

    private void zero() {
        signalShift(pos_x, 100 + logic_high);
        signalMove(distance, 0);
    }

    private void one() {
        signalShift(pos_x, 100 + logic_low);
        signalMove(distance, 0);
    }

    private void invalid() {
    }

    public static void main(String[] args) {
        String signal = JOptionPane.showInputDialog("Enter signal to be encoded");
        int choice = Integer.parseInt(JOptionPane.showInputDialog("Choose a type of Encoding:\n" +
                "1) Unipolar NRZ\n" +
                "2) Polar NRZ\n" +
                "3) Bipolar\n" +
                "5) RZ\n"));

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                BipolarLineEncodingPlot plot = new BipolarLineEncodingPlot(signal);
                plot.setVisible(true);
                plot.initGraph();

                switch (choice) {
                    case 1: {
                        break;
                    }
                    case 2: {
                        break;
                    }
                    case 3: {
                        break;
                    }
                    case 5: {
                        break;
                    }
                   
                }
            }
        });
    }
}
