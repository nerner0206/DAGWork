using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tape : MonoBehaviour
{
    //  取得したか
    private bool m_isTape = false;
    //  ローカル座標
    private Vector3 m_position;
    //  角度
    private float m_angle;

    //  受け渡し
    public bool GetSetTape
    {
        get { return m_isTape; }
        set { m_isTape = value; }
    }

    private void Start()
    {
        m_position = this.transform.localPosition;
        m_angle = 0f;
    }

    private void Update()
    {
        m_angle += Time.deltaTime;
        m_position = this.transform.localPosition;

        m_angle %= 360f;

        float posY = Mathf.Cos(m_angle) * 0.001f;

        Vector3 delta = new Vector3(0f, posY, 0f);
        
        this.transform.localPosition = m_position + delta;
    }

    //  初期化
    public void Init()
    {
        m_isTape = false;
    }

    //  当たり判定
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  取得済みにする
        m_isTape = true;
    }
}
