/**********************************************************************************************
* Programmer: Nicholas Waszkiewicz
* Professor: Dr. Tao
* Final Project
* Token.java
* Class to define Tokens
**********************************************************************************************/


public class Token{
	private String token;
	private int frequency;
	private int docFrequency = 0;
	private int lastDocInput = -1;//checks to see what the last doc that added to the doc freq was
	private String type;
	private double IDF;
	
	public String toString(){
		return token + " " + frequency + " " + IDF + " " + type;
	}
	public Token(String token, int frequency, double IDF, String type){
		this.token = token;
		this.frequency = frequency;
		this.IDF = IDF;
		this.type = type;
	}
	public void incDocFreq(int docNum){
		if(lastDocInput != docNum){
			lastDocInput = docNum;
			++docFrequency;
		}
	}
	
	public String getToken(){
		return token;
	}
	public int getFrequency(){
		return frequency;
	}
	public int getDocFrequency(){
		return docFrequency;
	}
	public double getIDF(){
		return IDF;
	}
	public String getType(){
		return type;
	}
}