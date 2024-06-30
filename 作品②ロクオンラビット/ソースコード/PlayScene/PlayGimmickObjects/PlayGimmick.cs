using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class PlayGimmick : Sound
{
    //  AudioSource
    protected AudioSource m_audioSource;
    //  ヒットした音の種類
    protected SoundKind m_hitSoundKind;

    //  渡す
    public SoundKind GetIsSoundHit() { return m_hitSoundKind; }
    //  取得
    public void SetIsSoundHit(SoundKind flag) { m_hitSoundKind = flag; }

    private void Start()
    {
        //  初期化
        m_audioSource = gameObject.GetComponent<AudioSource>();

        m_hitSoundKind = SoundKind.Over;
        
        Init();
    }

    //  初期化
    public virtual void Init() { }

    //  音がヒットした
    public virtual void SoundHit(
        SoundKind kind,         //  音の種類
        float pitch,          //  再生方法
        AudioClip audioClip     //  音素材
        ) { }

    //  音が離れた
    public virtual void SoundNot() 
    {
        //  音を消す
        m_hitSoundKind = SoundKind.Over;
    }

    //  リセット
    public virtual void GimmickReset() { }

    //  スイッチによるOn
    public virtual void SwichOn() { }

    //  スイッチによるOff
    public virtual void SwichOff() { }

    //  当たり判定
    public virtual void OnTriggerEnter2D(Collider2D collision)
    {
        //  音が触れていない
        if (!collision.gameObject.CompareTag("Sound")) return;

        //  音の種類
        SoundKind kind = collision.gameObject.gameObject.GetComponent<Sound>().GetSoundKind();

        //  AudioSourceを取得
        AudioSource audioSource = collision.gameObject.GetComponent<AudioSource>();

        //  音の再生方法
        float pitch = audioSource.pitch;
        //  音の素材
        AudioClip audioClip = audioSource.clip;

        //  音がヒット処理
        SoundHit(kind, pitch, audioClip);
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        //  音が触れていない
        if (!collision.gameObject.CompareTag("Sound")) return;

        SoundNot();
    }
}
