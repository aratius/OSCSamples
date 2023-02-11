using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OscJack;

public class OscSender : MonoBehaviour
{
    [SerializeField] string m_Ip = "127.0.0.1";
    [SerializeField] int m_Port = 12000;

    OscClient m_Client;

    void Awake()
    {
        m_Client = new OscClient(m_Ip, m_Port);
    }

    public void Send(string address, int value)
    {
        m_Client.Send(address, value);
    }

    public void Send(string address, float value)
    {
        m_Client.Send(address, value);
    }

    public void Send(string address, string value)
    {
        m_Client.Send(address, value);
    }

}
