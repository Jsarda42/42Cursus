import random
from faker import Faker
from django.contrib.auth.models import User
from django.core.management.base import BaseCommand
from django.db import transaction
from transcendence.models import Profile, MatchHistory, Connected

class Command(BaseCommand):
    help = 'Populate the database with fake users and profiles'

    def handle(self, *args, **kwargs):
        fake = Faker()
        num_users = 10  # Nombre d'utilisateurs à créer

        with transaction.atomic():  # Assure que toutes les modifications sont faites en une seule transaction
            profiles = []

            for _ in range(num_users):
                username = fake.user_name()
                email = fake.email()
                password = 'password123'  # Mot de passe par défaut
                bio = fake.text(max_nb_chars=200)

                # Création de l'utilisateur
                user = User.objects.create_user(username=username, email=email, password=password)

                Connected.objects.create(user=user)

                profile = Profile.objects.create(
                    user=user,
                    bio=bio,
                    avatar=None,
                    wins=random.randint(0, 100),
                    losses=random.randint(0, 100),
                    room=random.choice([True, False]),
                    is_2fa_enabled=random.choice([True, False]),
                )

                profiles.append(profile)

                # Ajouter des amis au hasard
                if len(profiles) > 1:  # Vérifie qu'il existe au moins un autre profil
                    friends = random.sample(profiles[:-1], random.randint(0, min(5, len(profiles) - 1)))
                    for friend in friends:
                        profile.friends.add(friend)

                # Ajouter des MatchHistory
                if len(profiles) > 1:  # Vérifie qu'il existe au moins un autre profil pour les matchs
                    num_matches = random.randint(1, 15)  # Nombre de matchs aléatoires par utilisateur
                    for _ in range(num_matches):
                        opponent = random.choice(profiles)
                        while opponent == profile:  # Éviter que l'utilisateur joue contre lui-même
                            opponent = random.choice(profiles)
                        
                        MatchHistory.objects.create(
                            user=profile.user,
                            opponent_username=opponent.user.username,
                            user_score=random.randint(0, 10),
                            opponent_score=random.randint(0, 10),
                        )

                self.stdout.write(f"Créé : {profile.id} -> {user.username} ({user.email}), 2FA: {profile.is_2fa_enabled}")

        self.stdout.write("Population de la base de données terminée avec succès !")

print("La commande populate_users est chargée")
