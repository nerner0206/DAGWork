using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.ParticleSystemJobs;

public class WindMove : MonoBehaviour
{
    [SerializeField, Header("���̗�")]
    private float m_windPower = 1.0f;

    [SerializeField, Tooltip("�ŏ��̗͂̕���")]
    private Vector2 m_defPowerDir;
    [SerializeField, Tooltip("�G�t�F�N�g")]
    private ParticleSystem m_particle;

    //  �ŏ��̗�
    private Vector2 m_windForce;

    //  ���̊����̒萔
    const float WIND_RATIO = 3.0f;

    public void Start()
    {
        PlayFront();
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        //  Rigidbody2D���������Ă��Ȃ�
        if (!collision.gameObject.GetComponent<Rigidbody2D>()) return;

        //  player�ł͂Ȃ�
        if (!collision.gameObject.CompareTag("Player")) return;

        //  �擾
        Rigidbody2D rb2D = collision.gameObject.GetComponent<Rigidbody2D>();
        //  �͂�^����
        rb2D.AddForce(m_windForce * m_windPower, ForceMode2D.Force);
    }

    //  ���]
    public void PlayBack()
    {
        m_windForce = m_defPowerDir * -1;

        //  �G�t�F�N�g�̌���
        var fo = m_particle.forceOverLifetime;
        fo.enabled = true;

        fo.xMultiplier = m_windForce.x * WIND_RATIO;
        fo.yMultiplier = m_windForce.y * WIND_RATIO;
    }
    //  �߂�
    public void PlayFront()
    {
        m_windForce = m_defPowerDir;

        //  �G�t�F�N�g�̌���
        var fo = m_particle.forceOverLifetime;
        fo.enabled = true;

        fo.xMultiplier = m_windForce.x * WIND_RATIO;
        fo.yMultiplier = m_windForce.y * WIND_RATIO;
    }
}
