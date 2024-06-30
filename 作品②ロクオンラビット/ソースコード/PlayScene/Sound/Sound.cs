using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//  音の種類
public enum SoundKind
{
    Water = 0,          //  水
    WoodBreak,          //  木破壊
    Electric,           //  電気
    Fire,               //  炎
    Motor,              //  モーター
    Door,               //  ドア
    Swich,              //  スイッチ
    Melt,               //  溶ける
    Wind,               //  風
    Beam,               //  ビーム
    GlassBreak,         //  ガラス破壊

    Over
}

public class Sound : MonoBehaviour
{
    [SerializeField, Tooltip("音の種類")]
    protected SoundKind m_soundKind;

    //  渡す
    public SoundKind GetSoundKind(){ return m_soundKind; }
    //  もらう
    public void SetSoundKind(SoundKind sound) { this.m_soundKind = sound; }
}
