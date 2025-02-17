using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class PlayGimmickSE : GimmickSE
{
    //  円の当たり判定
    private CircleCollider2D m_co2D = null;

    public void Init()
    {
        //  音の種類を消す
        m_soundKind = SoundKind.Over;
        //  円の当たり判定
        m_co2D = gameObject.GetComponent<CircleCollider2D>();
        //  当たり判定消す
        m_co2D.enabled = false;
    }
    public void OnGimmickSE(SoundKind kind)
    {
        //  音の種類
        m_soundKind = kind;

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
}
