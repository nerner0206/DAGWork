using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.ParticleSystemJobs;

public class WindMove : MonoBehaviour
{
    [SerializeField, Header("風の力")]
    private float m_windPower = 1.0f;

    [SerializeField, Tooltip("最初の力の方向")]
    private Vector2 m_defPowerDir;
    [SerializeField, Tooltip("エフェクト")]
    private ParticleSystem m_particle;

    //  最初の力
    private Vector2 m_windForce;

    //  風の割合の定数
    const float WIND_RATIO = 3.0f;

    public void Start()
    {
        PlayFront();
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        //  Rigidbody2Dを所持していない
        if (!collision.gameObject.GetComponent<Rigidbody2D>()) return;

        //  playerではない
        if (!collision.gameObject.CompareTag("Player")) return;

        //  取得
        Rigidbody2D rb2D = collision.gameObject.GetComponent<Rigidbody2D>();
        //  力を与える
        rb2D.AddForce(m_windForce * m_windPower, ForceMode2D.Force);
    }

    //  反転
    public void PlayBack()
    {
        m_windForce = m_defPowerDir * -1;

        //  エフェクトの向き
        var fo = m_particle.forceOverLifetime;
        fo.enabled = true;

        fo.xMultiplier = m_windForce.x * WIND_RATIO;
        fo.yMultiplier = m_windForce.y * WIND_RATIO;
    }
    //  戻す
    public void PlayFront()
    {
        m_windForce = m_defPowerDir;

        //  エフェクトの向き
        var fo = m_particle.forceOverLifetime;
        fo.enabled = true;

        fo.xMultiplier = m_windForce.x * WIND_RATIO;
        fo.yMultiplier = m_windForce.y * WIND_RATIO;
    }
}
