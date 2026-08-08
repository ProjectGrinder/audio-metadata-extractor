extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
    var audio_bytes: PackedByteArray = FileAccess.get_file_as_bytes("res://test.mp3")
    var res: Dictionary = AudioMetadataExtension.extract_metadata(audio_bytes)
    print(res)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
    pass
