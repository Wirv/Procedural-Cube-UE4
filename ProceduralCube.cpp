// Fill out your copyright notice in the Description page of Project Settings.

#include "Table2.h"
#include "Engine.h"

// Sets default values
ATable2::ATable2()
{
	ThisScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ThisScene;

	ThisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GenerateMesh"));
	ThisMesh->SetupAttachment(RootComponent);

}

void ATable2::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

void ATable2::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();
}

void ATable2::GenerateMesh()
{
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	Tangents.Reset();
	UVs.Reset();
	Colors.Reset();

	int32 TriangleIndexCount = 0;
	FVector DefinedShape[8];
	FProcMeshTangent TangentSetup;

	DefinedShape[0] = FVector(CubeRaduis.X, CubeRaduis.Y, CubeRaduis.Z); // Forward Top Right
	DefinedShape[1] = FVector(CubeRaduis.X, CubeRaduis.Y, -CubeRaduis.Z); // Forward Bottom Right
	DefinedShape[2] = FVector(CubeRaduis.X, -CubeRaduis.Y, CubeRaduis.Z); // Forward Top Left
	DefinedShape[3] = FVector(CubeRaduis.X, -CubeRaduis.Y, -CubeRaduis.Z); // Forward Bottom Left

	DefinedShape[4] = FVector(-CubeRaduis.X, -CubeRaduis.Y, CubeRaduis.Z); // Forward Top Right
	DefinedShape[5] = FVector(-CubeRaduis.X, -CubeRaduis.Y, -CubeRaduis.Z); // Forward Bottom Right
	DefinedShape[6] = FVector(-CubeRaduis.X, CubeRaduis.Y, CubeRaduis.Z); // Forward Top Left
	DefinedShape[7] = FVector(-CubeRaduis.X, CubeRaduis.Y, -CubeRaduis.Z); // Forward Bottom Left

	//front
	TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
	AddQuadMesh(DefinedShape[0], DefinedShape[1], DefinedShape[2], DefinedShape[3], TriangleIndexCount, TangentSetup);

	//Left
	TangentSetup = FProcMeshTangent(1.f, 0.f, 0.f);
	AddQuadMesh(DefinedShape[2], DefinedShape[3], DefinedShape[4], DefinedShape[5], TriangleIndexCount, TangentSetup);

	//Back
	TangentSetup = FProcMeshTangent(0.f, -1.f, 0.f);
	AddQuadMesh(DefinedShape[4], DefinedShape[5], DefinedShape[6], DefinedShape[7], TriangleIndexCount, TangentSetup);

	//Right
	TangentSetup = FProcMeshTangent(-1.f, 0.f, 0.f);
	AddQuadMesh(DefinedShape[6], DefinedShape[7], DefinedShape[0], DefinedShape[1], TriangleIndexCount, TangentSetup);

	//top
	TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
	AddQuadMesh(DefinedShape[6], DefinedShape[0], DefinedShape[4], DefinedShape[2], TriangleIndexCount, TangentSetup);

	//Bottom
	TangentSetup = FProcMeshTangent(0.f, -1.f, 0.f);
	AddQuadMesh(DefinedShape[1], DefinedShape[7], DefinedShape[3], DefinedShape[5], TriangleIndexCount, TangentSetup);

	ThisMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
}

void ATable2::AddTriangleMesh(FVector TopRight, FVector BottomRight, FVector BottomLeft, int32 & TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(BottomLeft);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	FVector ThisNorm = FVector::CrossProduct(TopRight, BottomRight).GetSafeNormal();
	for (int i = 0; i < 3; i++)
	{

		Normals.Add(ThisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);

	}
	UVs.Add(FVector2D(0.f, 1.f)); // Top Left
	UVs.Add(FVector2D(0.f, 0.f)); // Bottom Left
	UVs.Add(FVector2D(1.f, 0.f)); // Bottom Right


}

void ATable2::AddQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32 & TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;
	int32 Point4 = TriIndex++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(TopLeft);
	Vertices.Add(BottomLeft);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	Triangles.Add(Point4);
	Triangles.Add(Point3);
	Triangles.Add(Point2);

	FVector ThisNorm = FVector::CrossProduct(TopLeft - BottomRight, TopLeft - TopRight).GetSafeNormal();
	for (int i = 0; i < 4; i++)
	{

		Normals.Add(ThisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);

	}
	UVs.Add(FVector2D(0.f, 1.f)); // Top Left
	UVs.Add(FVector2D(0.f, 0.f)); // Bottom Left
	UVs.Add(FVector2D(1.f, 1.f)); // Top Right
	UVs.Add(FVector2D(1.f, 0.f)); // Bottom Right
}
