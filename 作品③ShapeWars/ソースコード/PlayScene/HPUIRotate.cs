using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HPUIRotate : MonoBehaviour
{
    //  ƒJƒƒ‰‚ÌŒü‚«‚Éİ’è
    void LateUpdate()
    {
        //@ƒJƒƒ‰‚Æ“¯‚¶Œü‚«‚Éİ’è
        transform.rotation = Camera.main.transform.rotation;
    }
}
