using UnityEngine;
using UnityEngine.InputSystem;

public class CameraController : MonoBehaviour
{
    public float MoveSpeed = 1.0f;
    public float LookSpeed = 1.0f;

    public bool bIsMenuButton { get; set; } = false;
    public delegate void MenuToggleDelegate();
    public event MenuToggleDelegate OnMenuToggle;

    bool bIsControlActive = false;
    float yawAxisValue = 0.0f;
    float pitchAxisValue = 0.0f;
    Vector3 movementDirection = Vector3.zero;
    Vector2 lookDirection = Vector2.zero;

    void Update()
    {
        Control();
    }

    void Control()
    {
        if (bIsControlActive)
        {
            transform.Translate(movementDirection * MoveSpeed * Time.deltaTime, Space.Self);

            Vector3 InputRotation = new Vector3(lookDirection.y, lookDirection.x, 0.0f);
            
            yawAxisValue += InputRotation.y * LookSpeed;
            pitchAxisValue += InputRotation.x * LookSpeed;

            pitchAxisValue = Mathf.Clamp(pitchAxisValue, -35.0f, 35.0f);

            Vector3 cameraRotateDirection = new Vector3(pitchAxisValue, yawAxisValue, 0.0f);

            transform.rotation = Quaternion.Euler(cameraRotateDirection);
        }
    }

    public void OnMove(InputValue inputValue)
    {
        if (bIsControlActive)
        {
            Vector2 inputDirection = inputValue.Get<Vector2>();
            movementDirection = new Vector3(inputDirection.x, 0.0f, inputDirection.y);
        }
    }

    public void OnLook(InputValue inputValue)
    {
        if (bIsControlActive)
        {
            lookDirection = inputValue.Get<Vector2>();
            lookDirection = new Vector2(lookDirection.x, lookDirection.y);
        }
    }

    public void OnActiveControll(InputValue inputValue)
    {
        bIsControlActive = inputValue.isPressed;
    }

    public void OnMenuButton()
    {
        OnMenuToggle?.Invoke();
    }
}
