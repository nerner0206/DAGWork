using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimatorManager : MonoBehaviour
{
    //  文字列
    private static readonly float[] attacks = {
        0.0f,
        0.2f,
        0.4f,
        0.6f,
        0.8f,
        1.0f};

    [SerializeField] private GameObject p;

    //  アニメータを設定する
    public void SetAnimClip(int num)
    {
        if(num > attacks.Length - 1) return;
        p.GetComponent<Animator>().SetFloat("attack", attacks[num]);
    }
}
