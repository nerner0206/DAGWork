using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum AllScene
{
    LogoScene,
    TitleScene,
    SelectScene,
    PlayScene,
};

public class SceneManagement : MonoBehaviour
{
    [SerializeField, Header("次のシーン候補")]
    protected string[] m_nextSceneNames;
    [SerializeField, Header("フェイドタイム")]
    protected float m_fadeTime = 1.0f;
    [SerializeField, Tooltip("オプション")]
    protected GameObject m_optionPrefab;

    //  オプションを開ける判定の取得
    public virtual bool NonOptionState() { return false; }
}
