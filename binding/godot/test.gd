extends Node2D
@onready var texture_rect: TextureRect = $TextureRect


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
    var audio_bytes: PackedByteArray = FileAccess.get_file_as_bytes("res://test.mp3")
    var meta: Dictionary = AudioMetadataExtension.extract_metadata(audio_bytes);
    print(meta)
    var res: Dictionary = AudioMetadataExtension.extract_image(audio_bytes)
    if (res.is_empty() or not res.has("IMAGE_DATA")):
        return
    
    var image_bytes: PackedByteArray = res["IMAGE_DATA"]
    var mime: String = res.get("MIME", "")
    
    var image: Image = Image.new()
    var err: Error = OK
    if "png" in mime.to_lower():
        err = image.load_png_from_buffer(image_bytes)
    else:
        err = image.load_jpg_from_buffer(image_bytes)
        
    if err != OK:
        print("Failed to decode image buffer! Error code: ", err)
        return
    
    var texture: ImageTexture = ImageTexture.create_from_image(image)
    texture_rect.texture = texture


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
    pass
