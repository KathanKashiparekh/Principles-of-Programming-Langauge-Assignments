import java.util.Random;

public class Tab implements Listener{
	private int noOfTasks;
	private String name;
	private float totalTime;
	private float timeExpired;

	public Tab(int noOfTasks,String name){
		this.noOfTasks=noOfTasks;
		this.name=name;
		this.timeExpired=0;
		this.totalTime=0;
		begin();
	}

	//Start noOfTasks Task threads. Each with some value. Store the sum in totalTime
	public void begin(){
		MyTabSource m=new MyTabSource(this);
		Random rand=new Random();
		Thread tasks[]=new Thread[noOfTasks];
		int taskSize;
		for(int i=0;i<noOfTasks;i++)
		{
			taskSize=rand.nextInt(1001)+1000;
			totalTime+=taskSize;
			tasks[i]=new Thread(new Task(taskSize,m));
		}
		System.out.println("Total size of tasks:"+totalTime);
		for (int i=0;i<noOfTasks;i++)
		{
			tasks[i].start();
		}
	}

	public synchronized void onEvent(int size){
		timeExpired+=size;
		if(timeExpired==totalTime){
			System.out.print(name+" Loaded "+((timeExpired/totalTime)*100)+" %");
			System.out.println(" Tab idle.");
		}
		else{
			System.out.println(name+" Loaded "+((timeExpired/totalTime)*100)+" %");
		}
	}
}