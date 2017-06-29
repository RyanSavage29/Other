import java.util.Scanner;

  ArrayList<String> title = new ArrayList<String>();
  ArrayList<Float> pol = new ArrayList<Float>();
  ArrayList<Float> ent = new ArrayList<Float>();
  ArrayList<Float> date = new ArrayList<Float>();
  float maxDate = 0;
  float maxWidth = 0;
  float height = 800;
  float width = 800;
  float minDate = -1;

void setup() {

  Scanner input;
  String[] data = loadStrings("docVectors.txt"); //text file with info
 
 //title ||| political score ||| entertainment score ||| date
   //System.out.println("Start");
   
   //feed text file into arraylists
  for (int i = 0; i < data.length; i++) //<>//
  {
    //data[i] = data[i].replaceAll("\\|\\|\\|","___");
    
    input = new Scanner(data[i]).useDelimiter("\\|\\|\\|");
   
    for(int j = 0; input.hasNext(); j++) //for each line
    {
      if (j==0) //title
      {
        title.add(input.next());
      }
      else if (j == 1) //political score
      {
        Float temp = input.nextFloat();
        if (temp > maxWidth)
          maxWidth = temp;
        pol.add(temp);
      }
      else if (j == 2) //entertainment score
      {
        Float temp = input.nextFloat();
        if (temp > maxWidth)
          maxWidth = temp;
        ent.add(temp);
      }
      else if (j == 4) //date score
      {
        Float temp = input.nextFloat();
        if (temp > maxDate)
          maxDate = temp;
        if (temp < minDate)
          minDate = temp;
        else
        {
          if (minDate == -1)
            minDate = temp;
        }
        
        date.add(temp);
      }
    }
 
    //System.out.println("line " + i + ": " + data[i]);
  }
  //System.out.println("Stop");
  //System.out.println(maxWidth);
  //System.out.println(maxDate);
  
  //draw
  size(800, 800, P2D);
  
  background(200, 220, 200);
  textSize(32);
  fill(0, 0, 256);
  text("Entertainment", 10, 50);
  textSize(32);
  fill(256, 0, 0);
  text("Politics", 650, 750);
  
  for (int i = date.size() - 1; i >= 0; i--)
  {
      float coor[] = newCoor(pol.get(i), ent.get(i), date.get(i));
      fill(color(256 - (256 * (ent.get(i)/maxWidth)), 256, 256 - (256 * (pol.get(i)/maxWidth))));
      //noStroke();
      ellipse(coor[0], coor[1], coor[2], coor[2]);
      pol.remove(i);
      ent.remove(i);
      date.remove(i);
  }
}


void draw()
{
    
 
}

public float[] newCoor(Float pol, Float ent, Float date)
{
  float result[] = new float[3]; //x, y, z
  result [0] = 0;   //x
  result [1] = 0;   //y
  result [2] = 10;  //z
  
  //new X component - political component
  result[0] = pol * width / maxWidth;
  
  //new Y component - entertainment component
  result[1] += 800 - (ent * width / maxWidth);
  
  //new Z compnent - date
  
  //System.out.println(pol + " " + ent + " " + date + "\n" + result[0] + " " + result[1] + " " + result[2]);
  return result;
}