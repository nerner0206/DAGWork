using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    public static SoundManager instance;

    [SerializeField] private AudioClip audioClip;

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(instance);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    public void ButtonSE()
    {
        //  ‰¹—Ê‚ðŽæ“¾
        float v = gameObject.GetComponent<AudioSource>().volume;
        gameObject.GetComponent<AudioSource>().volume = 1.0f;
        gameObject.GetComponent<AudioSource>().PlayOneShot(audioClip);
        gameObject.GetComponent<AudioSource>().volume = v;
    }
}
