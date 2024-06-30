using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(SpriteRenderer))]
public class Map : MonoBehaviour
{
    [SerializeField, Tooltip("デフォルトマテリアル")]
    private Material m_defMaterial;
    [SerializeField, Tooltip("アウトラインマテリアル")]
    private Material m_outLineMaterial;
    [SerializeField, Tooltip("SpriteRenderer")]
    private SpriteRenderer m_spriteRenderer;

    //  アイコンがマップ上にある
    public void SetOnIcon()
    {
        //  アウトラインマテリアルに変更
        m_spriteRenderer.material = m_outLineMaterial;
    }
    //  アイコンがマップ上にない
    public void SetRemoveIcon()
    {
        //  ノーマルのマテリアルに戻す
        m_spriteRenderer.material = m_defMaterial;
    }
}
