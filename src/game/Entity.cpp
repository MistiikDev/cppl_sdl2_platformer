#include "Game.h"
#include "Entity.h"

Entity::Entity(Game *game, const EntityData &data, std::shared_ptr<SDL_Texture> texture) : 
    CurrentGameInstance(game),                               
    Position(data.Position),                                                                     
    Mass(data.Mass),                                                                        
    Texture(texture),                                                                    
    DefaultTexture(texture),
    RenderingGroup(data.RenderingGroup),         
    RenderingLayer(data.RenderingLayer),
    Anchored(data.Anchored),                                       
    CanCollide(data.CanCollide),
    Name(data.Name),
    isPassive(data.Passive),
    fixedToCamera(data.fixedToCamera)
{
    BoundingBox.x = 0;
    BoundingBox.y = 0;

    TextureManager::QueryTexture(this->Texture, &BoundingBox.w, &BoundingBox.h); // Set BoundingBox data
    
    this->ID = data.ID ? data.ID : static_cast<uint64_t>(Position.x) << 32 | static_cast<uint32_t>(Position.y);; // Generate Random ID if not already specified;
    
    this->AnchordPoint.x = BoundingBox.w / 2;
    this->AnchordPoint.y = BoundingBox.h / 2; // Set as default

    Rotation = 0;
    DirectionFacing = SDL_FLIP_NONE;
    ClassName = (ClassName.empty() ? ClassName : "Generic_Entity");

    //std::cout << "ENTITY : Loaded Entity : '" << this->Name << "' with ID : " << this->ID << std::endl;
};

void Entity::Awake()
{    
    this->animator = std::make_unique<Animator>(this);
   
    auto it = AnimationLoader::AnimationPackage.find(this->ClassName);
    if (it == AnimationLoader::AnimationPackage.end()) {
        //std::cerr << "No animation package found for class: " << this->ClassName << std::endl;
        return;
    }
    
    for (const AnimationData& data : it->second) {
        std::unique_ptr<AnimationTrack> track = AnimationLoader::LoadTrackFromDefinition(data, this);

        if (track) {
            this->LoadedAnimations[data.Name] = std::move(track);
        }
    }
}

void Entity::SetPosition(Vec2f &newposition, bool stayInBounds = true)
{
    int w = this->BoundingBox.w;
    int h = this->BoundingBox.h;
    int screen_w, screen_h;
    
    this->CurrentGameInstance->GetLogicalWindowSize(screen_w, screen_h);

    // new position.coord = clamp(0, screen_width - player_width, coord); -> screen_width - player_width = account for texture thickness!

    // newposition.x = (stayInBounds ? std::max(0.0, std::min((double)(screen_w - w), newposition.x)) : newposition.x);
    // newposition.y = (stayInBounds ? std::max(0.0, std::min((double)(screen_h - h), newposition.y)) : newposition.y);

    this->Position = newposition;
}

void Entity::Push(Vec2f &push_vector, float speed)
{
    if (this->isPushing) {
        return;
    }
    
    this->isPushing = true;

    Vec2f startPosition = this->GetPosition();
    Vec2f targetPosition = startPosition + push_vector;
    for (int i = 0; i <= 100; i++)
    {
        float t = static_cast<float>(i) / 100.0f;
        Vec2f lerpedPosition = startPosition.Lerp(targetPosition, t);

        this->SetPosition(lerpedPosition, true);
    }

    this->isPushing = false;
}

void Entity::Update(float deltaTime) {
    if (this->isPassive) return;
    
    this->animator->UpdateAnimations(deltaTime);
}
