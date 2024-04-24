using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Text;
using System;
using UnityEngine.PlayerLoop;
using UnityEngine.UI;

public class arduino_Control : MonoBehaviour
{
    [SerializeField] GamepadManager gamepad_manager;
    [SerializeField] Canvas_manager canvas_manager;


    [SerializeField] int gelen_veri_sayisi;

    public SerialPort serialPort;
    public string com;

    string gelen_deger;

    [SerializeField] byte[] gonderilcek_veri = new byte[16]; //new byte[10];
    [SerializeField] byte toplam = 0;

    [SerializeField] byte throttle;
    [SerializeField] byte yaw;
    [SerializeField] byte rol;
    [SerializeField] byte pitch;

    [SerializeField] byte throttle_2;

    [SerializeField] byte rt;
    [SerializeField] byte lt;

    [SerializeField] byte btn_rb, btn_lb;
    [SerializeField] byte btn_y;
    [SerializeField] byte btn_x;
    [SerializeField] byte btn_b;
    [SerializeField] byte btn_a;

    [SerializeField] byte btn_right;

    private void Awake()
    {
        gameObject.SetActive(false);
    }
    

    void OnEnable()
    {
        com = canvas_manager.com_field.text;

        serialPort = new SerialPort("COM" + com, 9600); // Arduino'nun bağlı olduğu port ve baud hızı
        Debug.Log("COM" + com);
        try
        {
            serialPort.Open();
            canvas_manager.com_kaydet(com);
        }
        catch (Exception ex)
        {
            Debug.LogError(ex.ToString());
        }
        Debug.Log("Seri port acildi.");

        StartCoroutine(kumanda_verisi_baslat());
    }

    IEnumerator kumanda_verisi_baslat()
    {
        while (true)
        {
            throttle = (byte)((Mathf.Round((gamepad_manager.throttle + 1) * 100) / 100) * 100);
            rol = (byte)((Mathf.Round((gamepad_manager.rol + 1) * 100) / 100) * 100);
            throttle_2 = (byte)((Mathf.Round((gamepad_manager.throttle_2 + 1) * 100) / 100) * 100);

            rt = (byte)((Mathf.Round((gamepad_manager.rt + 1) * 100) / 100) * 100);
            lt = (byte)((Mathf.Round((gamepad_manager.lt + 1) * 100) / 100) * 100);

            btn_rb = (byte)(gamepad_manager.btn_rb + 1);
            btn_lb = (byte)(gamepad_manager.btn_lb + 1);

            btn_y = (byte)(gamepad_manager.btn_y + 1);
            btn_x = (byte)(gamepad_manager.btn_x + 1);
            btn_b = (byte)(gamepad_manager.btn_b + 1);
            btn_a = (byte)(gamepad_manager.btn_a + 1);

            btn_right = (byte)(gamepad_manager.btn_right + 1);

            toplam = (byte)((throttle / 2) + (rol / 2));


            gonderilcek_veri[0] = throttle;
            gonderilcek_veri[1] = rol;
            gonderilcek_veri[3] = toplam;

            gonderilcek_veri[4] = rt;
            gonderilcek_veri[5] = lt;

            gonderilcek_veri[6] = btn_y;
            gonderilcek_veri[7] = btn_x;
            gonderilcek_veri[8] = btn_b;
            gonderilcek_veri[9] = btn_a;

            gonderilcek_veri[10] = btn_rb;
            gonderilcek_veri[11] = btn_lb;

            gonderilcek_veri[12] = btn_right;

            if(throttle_2 == 100)
            {
                throttle_2 = 99;
            }
            gonderilcek_veri[13] = throttle_2;


            serialPort.WriteLine("256");
            serialPort.Write(gonderilcek_veri, 0, gonderilcek_veri.Length);


            yield return new WaitForSeconds(0.1f);
        }
    }

    void OnApplicationQuit()
    {
        if (serialPort != null && serialPort.IsOpen)
        {
            serialPort.Close();
        }
    }
    private void OnDestroy()
    {
        if (serialPort != null && serialPort.IsOpen)
        {
            serialPort.Close();
            Debug.Log("Seri port kapatildi.");
        }
    }
}