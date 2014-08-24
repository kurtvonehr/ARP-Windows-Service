using System;
using System.ServiceProcess;
using System.ComponentModel;
using System.Configuration.Install;
using System.Threading;
using System.Diagnostics;
using System.Net;
using System.Net.NetworkInformation;
using System.Text;
using System.IO.Ports;

public class CronService : ServiceBase
{ 
  private CronJob job;
  private Timer stateTimer; 
  private TimerCallback timerDelegate;
  
  public CronService()
  {
    this.ServiceName = "WIFI_DOOR_LOCK";
    this.CanStop = true;
    this.CanPauseAndContinue = false;
    this.AutoLog = true;
  }

  protected override void OnStart(string [] args)
  {
    job = new CronJob();
    timerDelegate = new TimerCallback(job.checkConnection);
    stateTimer = new Timer(timerDelegate, null, 15000, 15000);
  }
 
  protected override void OnStop()
  {
   stateTimer.Dispose();
  }
 
  public static void Main()
  { 
   System.ServiceProcess.ServiceBase.Run(new CronService());
  }
}

[RunInstaller(true)]
public class CronInstaller : Installer
{
  private ServiceProcessInstaller processInstaller;
  private ServiceInstaller serviceInstaller;

  public CronInstaller()
  {
    processInstaller = new ServiceProcessInstaller();
    serviceInstaller = new ServiceInstaller();

    processInstaller.Account = ServiceAccount.LocalSystem;
    serviceInstaller.StartType = ServiceStartMode.Automatic;
    serviceInstaller.ServiceName = "WIFI_DOOR_LOCK";

    Installers.Add(serviceInstaller);
    Installers.Add(processInstaller);
  } 
}

public class CronJob
{
  // The state object is necessary for a TimerCallback.
  public void checkConnection(object stateObject)
  {
        Process p = new Process();
		Ping pingSender = new Ping ();
        p.StartInfo.FileName = "arp";
        p.StartInfo.Arguments = "-a";
        p.StartInfo.UseShellExecute = false;
        p.StartInfo.RedirectStandardOutput = true;
		
		string data = "a";
         byte[] buffer = Encoding.ASCII.GetBytes (data);
		
		for(int i = 0; i < 25 ; i++){
			pingSender.Send ("10.0.0."+i.ToString(),10,buffer);
		}
		
        p.Start();	

        string output = p.StandardOutput.ReadToEnd();
        p.WaitForExit();
		
		string MAC = "xx-xx-xx-xx-xx-xx";
		if(output.Contains(MAC)){
			SerialPort port = new SerialPort("COM5", 9600);
            port.Open();
			port.Write("u");
			port.Close();
		}
		else{
			SerialPort port = new SerialPort("COM5", 9600);
            port.Open();
			port.Write("l");
			port.Close();
		}
  }
}  
