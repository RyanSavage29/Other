public class PageVector{
	private String title;
	private double pageVectors[] = new double[3];
	
	public PageVector(String title, String date){
		this.title = title;
		pageVectors[0] = 0.0;//POL
		pageVectors[1] = 0.0;//ENT
		int year = Integer.parseInt(date.substring(0,4));
		int month = Integer.parseInt(date.substring(4,6));
		int day = Integer.parseInt(date.substring(6,8));
		pageVectors[2] = (year-1987)*365 + (month-1)*30 + (day-1);//DATE
	}
	public String getTitle(){
		return title;
	}
	
	public void increaseVector(String type, double val){
		if(type.equals("p")){//adds to pol val
			pageVectors[0] += val;
		}
		else{//adds to ent val
			pageVectors[1] += val;
		}
	}
	
	
	public void normalizeVectors(){//check this just in case
		double bottomPart = 0.0;
		for(int i = 0; i < 2; ++i){
			bottomPart += (pageVectors[i] * pageVectors[i]);
		}
		bottomPart = Math.sqrt(bottomPart);
		
		for(int i = 0; i < 2; ++i){//nomalizes ONLY the POL and ENT vals
			pageVectors[i] = (pageVectors[i] / bottomPart);
			
		}
	}
	public String toString(){//DONE
		return title + "___" + pageVectors[0] + "___" + pageVectors[1] + "___" + pageVectors[2];
	}
}