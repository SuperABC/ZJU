package Frame;

import java.awt.EventQueue;

import javax.swing.JFrame;

public class Main extends JFrame {
	public static String srcPath = "C:\\Users\\MLKJ\\eclipse-workspace\\CSK\\src\\Source\\drawable\\";
	
	public static Table frame;
	
	public static void main(String[] args) {
	    EventQueue.invokeLater(new Runnable() {
			public void run() {
				frame = new Table(0);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	            frame.setTitle("CS Killer");
				frame.setVisible(true);
			}
	    });
	}
}

