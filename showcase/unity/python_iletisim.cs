using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using UnityEngine;
using UnityEngine.UI;

public class python_iletisim : MonoBehaviour
{
    public static python_iletisim instants { get; set; }

    [SerializeField] GamepadManager gamepadManager;

    [SerializeField] Button python_connect_btn;

    TcpClient socketConnection;
    NetworkStream stream;

    bool btn_basildi = false;

    [HideInInspector] public bool python_baglanildi = false;


    private void Awake()
    {
        instants = this;
    }

    void Start()
    {
        //ConnectToTcpServer();

        //StartCoroutine(SendDataAfterDelay());
    }

    public void ConnectToTcpServer()
    {
        try
        {
            socketConnection = new TcpClient("127.0.0.1", 5555);
            stream = socketConnection.GetStream();

            python_baglanildi = true;
            python_connect_btn.image.color = Color.green;
            Debug.Log("Bağlantı başarılı.");

            StartCoroutine(sirayla_veri_yolla());

        }
        catch (Exception ex)
        {
            python_baglanildi = false;
            Debug.LogError("Bağlantı başarısız.   " + ex);
            python_connect_btn.image.color = Color.white;
        } 

        

        
    }

    IEnumerator sirayla_veri_yolla()
    {
        yield return new WaitForSeconds(5f);

        for (int i = 0; i < Canvas_manager.instance.yellow; i++)
        {
            SendDataToPython("s");
            yield return new WaitForSeconds(0.5f);
        }
        Canvas_manager.instance.yellow = 0;

        for (int i = 0; i < Canvas_manager.instance.blue; i++)
        {
            SendDataToPython("m");
            yield return new WaitForSeconds(0.5f);
        }
        Canvas_manager.instance.blue = 0;

        for (int i = 0; i < Canvas_manager.instance.red; i++)
        {
            SendDataToPython("k");
            yield return new WaitForSeconds(0.5f);
        }
        Canvas_manager.instance.red = 0;

        for (int i = 0; i < Canvas_manager.instance.green; i++)
        {
            SendDataToPython("y");
            yield return new WaitForSeconds(0.5f);
        }
        Canvas_manager.instance.green = 0;
    }


    /*IEnumerator SendDataAfterDelay()
    {
        while (true)
        {
            yield return new WaitForSeconds(1f);
            SendDataToPython();
        }
    }*/

    private void Update()
    {
        if(gamepadManager.btn_a == 1 && gamepadManager.btn_lb == 0 && btn_basildi == false)
        {
            SendDataToPython("3");
            StartCoroutine(basma_delay());
        }
        if(gamepadManager.ikili_btn == 1 && btn_basildi == false)
        {
            SendDataToPython("w");
            StartCoroutine(basma_delay());
        }
    }

    public void SendDataToPython(string veri)
    {
        if(stream != null)
        {
            try
            {
                string message = veri;
                byte[] data = Encoding.ASCII.GetBytes(message);

                stream.Write(data, 0, data.Length);

                Debug.Log("Veri yollandi: " + message);
            }
            catch (Exception e)
            {
                Debug.LogError("Hata: " + e);
            }
        }
    }

    IEnumerator basma_delay()
    {
        btn_basildi = true;
        yield return new WaitForSeconds(0.5f);
        btn_basildi = false;
    }

    private void OnDestroy()
    {
        if (socketConnection != null)
        {
            socketConnection.Close();
        }
    }

    void OnApplicationQuit()
    {
        if (socketConnection != null)
        {
            socketConnection.Close();
        }
    }
}
