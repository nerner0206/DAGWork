using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TItleWeaponController : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //  ˆÊ’u‚âŠp“x‚ğ’²®‚·‚é
        gameObject.transform.position = new Vector3(Random.Range(-10.0f, 10.0f), 12.0f, 0.0f);
        gameObject.transform.localEulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
    }

    // Update is called once per frame
    void Update()
    {
        //  —‰º‚³‚¹‚é
        gameObject.transform.position = gameObject.transform.position + new Vector3(0.0f, -5.0f * Time.deltaTime, 0.0f);
        //  ‰ñ“]‚³‚¹‚é
        gameObject.transform.Rotate(new Vector3(0.0f, 0.0f, 200.0f * Time.deltaTime));

        //  ‰æ–Ê“à‚È‚çˆ—‚µ‚È‚¢
        if (gameObject.transform.position.y > -30.0f) return;

        //  ‰æ–ÊŠO‚ÉˆÚ“®‚µ‚½‚çíœ‚·‚é
        Destroy(gameObject);
    }
}
