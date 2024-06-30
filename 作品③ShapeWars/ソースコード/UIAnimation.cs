using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class UIAnimation : MonoBehaviour
{
    [SerializeField] private Image fillImage;
    [SerializeField] private List<Image> buttonImages;
    [SerializeField] private Color rollColor;
    [SerializeField] private Text texts;
    private Color baseColor;

    [SerializeField] private float scale;
    [SerializeField] private float speed;

    private bool hitting;

    // Start is called before the first frame update
    void Start()
    {
        hitting = false;

        fillImage.rectTransform.sizeDelta = Vector2.zero;
        baseColor = buttonImages[0].color;
    }

    // Update is called once per frame
    void Update()
    {
        //  ƒAƒCƒRƒ“‚ª“–‚½‚Á‚Ä‚½‚ç
        bool hit = gameObject.GetComponent<UIHit>().hit;

        if(!hitting && hit)
        {
            hitting = true;

            fillImage.rectTransform.DOSizeDelta(Vector2.one * scale, speed);
            foreach(var buttonImage in buttonImages)
            {
                buttonImage.DOColor(rollColor, speed);
            }

            if (texts != null) texts.DOColor(rollColor, speed);
        }
        else if(hitting && !hit)
        {
            hitting = false;

            fillImage.rectTransform.DOSizeDelta(Vector2.zero, speed);
            foreach (var buttonImage in buttonImages)
            {
                buttonImage.DOColor(baseColor, speed);
            }
            if (texts != null) texts.DOColor(baseColor, speed);
        }
    }
}
