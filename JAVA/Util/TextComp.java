package Util;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JComponent;

public class TextComp extends JComponent {
	private String string;
	private Color color = new Color(0, 0, 0);
	private int posX = 0,  posY = 0;

	public TextComp(String text) {
		this.string = text;
	}
	public TextComp(String text, Color c) {
		this.string = text;
		this.color = c;
	}
	public TextComp(String text, int x, int y) {
		this.string = text;
		this.posX = x;
		this.posY = y;
	}
	public TextComp(String text, Color c, int x, int y) {
		this.string = text;
		this.posX = x;
		this.posY = y;
		this.color = c;
	}
	
	public void paintComponent(Graphics g) {
		g.setColor(color);
		g.setFont(new Font("Î¢ÈíÑÅºÚ", 0, 20));
		g.drawString(string, posX, posY);
	}
	public String getString() {
		return string;
	}
	public void setString(String s) {
		string = s;
	}

	public Dimension getPreferredSize() {
		return new Dimension(string.length()*10, 24);
	}
}
