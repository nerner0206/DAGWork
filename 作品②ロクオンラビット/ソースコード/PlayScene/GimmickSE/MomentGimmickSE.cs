using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class MomentGimmickSE : GimmickSE
{
    [SerializeField, Tooltip("円の当たり判定")]
    private CircleCollider2D m_co2D;
    //  時間
    private float m_timer;

    public void Init()
    {
        //  音の種類を消す
        m_soundKind = SoundKind.Over;
        //  当たり判定消す
        m_co2D.enabled = false;

        //  時間を0へ
        m_timer = 0.0f;
    }
    public void OnGimmickSE(SoundKind kind, float time)
    {
        //  音の種類
        m_soundKind = kind;
        //  音取得可能時間
        m_timer = time;

        //  当たり判定をつける
        m_co2D.enabled = true;
    }
    public void OffGimmickSE()
    {
        //  音の種類
        m_soundKind = SoundKind.Over;

        //  当たり判定をつける
        m_co2D.enabled = false;
    }

    private void Update()
    {
        //  音が無ければ処理しない
        if (m_soundKind == SoundKind.Over) return;

        if (m_timer > 0.0f)
        {
            //  時間を減らす
            m_timer -= Time.deltaTime;
            //  返す
            return;
        }

        //  当たり判定を削除
        OffGimmickSE();
    }
}
